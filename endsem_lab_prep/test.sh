#!/usr/bin/env bash
# Build every sol*.cpp as C++11 and check it against tests/*.in -> tests/*.out.
# Usage: ./test.sh                 all problems
#        ./test.sh dp/03_lcs heap  only these problem folders or topic folders
# Trailing spaces and the final newline are ignored; everything else must match.
cd "$(dirname "$0")" || exit 1
if [ -z "$CXX" ]; then
  CXX=g++
  for c in /opt/homebrew/bin/g++-15 /opt/homebrew/bin/g++-14; do [ -x "$c" ] && CXX=$c && break; done
fi
FLAGS="-std=c++11 -O2 -Wall -Wextra"
run10() { if command -v timeout >/dev/null; then timeout 10 "$@"; else perl -e 'alarm 10; exec @ARGV' "$@"; fi; }
BIN=$(mktemp -d); trap 'rm -rf "$BIN"' EXIT
targets=("$@"); [ ${#targets[@]} -eq 0 ] && targets=(templates dp hashing heap mock_papers)
dirs=()
for t in "${targets[@]}"; do
  while IFS= read -r d; do dirs+=("$d"); done < <(find "${t%/}" -name 'sol*.cpp' -exec dirname {} \; | sort -u)
done
pass=0; fail=0
for d in "${dirs[@]}"; do
  for src in "$d"/sol*.cpp; do
    exe="$BIN/$(echo "$src" | tr '/' '_')"
    if ! "$CXX" $FLAGS "$src" -o "$exe" 2>"$exe.log" || [ -s "$exe.log" ]; then
      echo "BUILD  $src"; sed 's/^/    /' "$exe.log" | head -20
      [ -x "$exe" ] || { fail=$((fail+1)); continue; }
    fi
    for in in "$d"/tests/*.in; do
      [ -e "$in" ] || continue
      exp=${in%.in}.out
      got=$(run10 "$exe" < "$in" 2>/dev/null | sed 's/[[:space:]]*$//')
      want=$(sed 's/[[:space:]]*$//' "$exp")
      if [ "$got" == "$want" ]; then pass=$((pass+1)); else
        fail=$((fail+1)); echo "FAIL   $src < $in"
        diff <(echo "$want") <(echo "$got") | head -8 | sed 's/^/    /'
      fi
    done
  done
done
echo "$pass passed, $fail failed  ($CXX $FLAGS)"
[ "$fail" -eq 0 ]
