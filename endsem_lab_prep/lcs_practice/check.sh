#!/usr/bin/env bash
# Check your LCS practice solution against a problem's tests.
# Usage: ./check.sh p3 my.cpp      build my.cpp (C++11) and run it on p3_*/tests
#        ./check.sh all            check the reference solutions in solutions/
[ $# -eq 2 ] && case "$2" in /*) ;; *) set -- "$1" "$PWD/$2" ;; esac   # make the source path absolute
cd "$(dirname "$0")" || exit 1
if [ -z "$CXX" ]; then
  CXX=g++
  for c in /opt/homebrew/bin/g++-15 /opt/homebrew/bin/g++-14; do [ -x "$c" ] && CXX=$c && break; done
fi
run10() { if command -v timeout >/dev/null; then timeout 10 "$@"; else perl -e 'alarm 10; exec @ARGV' "$@"; fi; }
BIN=$(mktemp -d); trap 'rm -rf "$BIN"' EXIT
check() {   # check <problem dir> <source>
  local exe="$BIN/$1" pass=0 fail=0
  "$CXX" -std=c++11 -O2 -Wall -Wextra "$2" -o "$exe" || { echo "BUILD FAILED: $2"; return 1; }
  for in in "$1"/tests/*.in; do
    got=$(run10 "$exe" < "$in" 2>/dev/null | sed 's/[[:space:]]*$//')
    want=$(sed 's/[[:space:]]*$//' "${in%.in}.out")
    if [ "$got" == "$want" ]; then pass=$((pass+1)); else
      fail=$((fail+1)); echo "FAIL  $in"
      diff <(echo "$want") <(echo "$got") | head -6 | sed 's/^/      /'
    fi
  done
  echo "$1: $pass passed, $fail failed"
  [ "$fail" -eq 0 ]
}
if [ "$1" == "all" ]; then
  ok=0; for s in solutions/*.cpp; do p=$(basename "$s" .cpp); check "$p" "$s" || ok=1; done; exit $ok
fi
[ $# -eq 2 ] || { sed -n 2,4p "$0"; exit 1; }
dir=$(ls -d "$1"_* 2>/dev/null | head -1)
[ -d "$dir" ] || { echo "no problem $1 (use p1..p10)"; exit 1; }
check "$dir" "$2"
