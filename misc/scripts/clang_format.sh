#!/usr/bin/env bash

# This script runs clang-format and fixes copyright headers on relevant files in the repo.

set -uo pipefail
IFS=$'\n\t'

# Check for our clang-format
if [ ! -f ./misc/clang_format_18 ]; then
    echo "Downloading clang-format v18 from https://github.com/muttleyxd/clang-tools-static-binaries/releases/download/master-796e77c/clang-format-18_linux-amd64"
    wget -q https://github.com/muttleyxd/clang-tools-static-binaries/releases/download/master-796e77c/clang-format-18_linux-amd64 -O ./misc/clang_format_18
    chmod +x ./misc/clang_format_18
fi

clang_fmt="./misc/clang_format_18"

header_worker="./misc/scripts/copyright_headers.py"

# File extensions to be formatted with clang-format
CLANG_FORMAT_FILE_EXTS=(".c" ".h" ".cpp" ".hpp" ".inc")

# Loop through all text files tracked by Git
git grep -zIl '' |
while IFS= read -rd '' f; do
    if [[ "$f" == "build/"* ]]; then
        continue
    elif [[ "$f" == "bin/"* ]]; then
        continue
    elif [[ "$f" == "symbols/"* ]]; then
        continue
    elif [[ "$f" == "vendor/"* ]]; then
        continue
    elif [[ "$f" == *".bat" ]]; then
        continue
    elif [[ "$f" == *"patch" ]]; then
        continue
    fi

    for extension in "${CLANG_FORMAT_FILE_EXTS[@]}"; do
        if [[ "$f" == *"$extension" ]]; then
            $clang_fmt --Wno-error=unknown -i "$f"
            "$header_worker" "$f"
            continue 2
        fi
    done
done

# Generate a patch to check for formatting issues
git diff --color > patch.patch

# If no patch is generated, all files comply with the style rules
if [ ! -s patch.patch ] ; then
    printf "Files in this commit comply with the clang-format style rules.\n"
    rm -f patch.patch
    exit 0
fi

# If a patch is generated, display the differences and exit with an error
printf "\n*** The following differences were found between the code "
printf "and the formatting rules:\n\n"
cat patch.patch
printf "\n*** Aborting, please fix your commit(s) with 'git commit --amend' or 'git rebase -i <hash>'\n"
rm -f patch.patch
exit 1
