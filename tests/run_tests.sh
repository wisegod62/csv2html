#!/bin/bash

# Exit instantly if any command fails
set -e

echo "🔨 Building project..."
make

echo "🏃 Running CSV to HTML engine..."
./csv2html tests/test_data.csv tests/output.html

echo "🔍 Validating output markup..."
# 'diff' compares the generated file against your known perfect file
if diff -q tests/output.html tests/expected.html > /dev/null; then
  echo "✅ TEST PASSED: Output matches expected structural HTML perfectly!"
else
  echo "❌ TEST FAILED: Output mismatch detected!"
  diff -u tests/expected.html tests/output.html
  exit 1
fi

# Optional Portfolio Flex: Check for memory leaks if 'valgrind' is installed
if command -v valgrind &> /dev/null; then
  echo "🧠 Running Valgrind memory analysis..."
  valgrind --leak-check=full --error-exitcode=1 ./csv2html tests/test_data.csv tests/output.html > /dev/null
  echo "✅ MEMORY PASSED: No leaks or illegal memory access detected!"
else
  echo "⚠️ Note: Install 'valgrind' to run automated memory-leak validations."
fi

echo "🎉 All system checks completed successfully!"
rm output.html
make clean
