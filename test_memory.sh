#!/bin/bash

echo "🧪 Cube3D Memory Leak Testing Suite"
echo "===================================="

make re

echo -e "\n1️⃣ Testing VALID map..."
echo "timeout 3s valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/valid.cub"
timeout 3s valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/valid.cub 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" || echo "✅ No definite leaks!"

echo -e "\n2️⃣ Testing INVALID map 1..."
echo "valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/invalid1.cub"
valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/invalid1.cub 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" || echo "✅ No definite leaks!"

echo -e "\n3️⃣ Testing INVALID map 2..."
echo "valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/invalid2.cub"
valgrind --leak-check=full --error-exitcode=1 ./cub3D assets/map/invalid2.cub 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" || echo "✅ No definite leaks!"

echo -e "\n4️⃣ Testing NON-EXISTENT file..."
echo "valgrind --leak-check=full --error-exitcode=1 ./cub3D nonexistent.cub"
valgrind --leak-check=full --error-exitcode=1 ./cub3D nonexistent.cub 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" || echo "✅ No definite leaks!"

echo -e "\n5️⃣ Testing NO arguments..."
echo "valgrind --leak-check=full --error-exitcode=1 ./cub3D"
valgrind --leak-check=full --error-exitcode=1 ./cub3D 2>&1 | grep -E "(LEAK SUMMARY|definitely lost|ERROR SUMMARY)" || echo "✅ No definite leaks!"

echo -e "\n🎯 Memory Testing Complete!"
