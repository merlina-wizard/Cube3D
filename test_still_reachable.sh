#!/bin/bash

echo "🧪 Testing Still Reachable Memory"
echo "================================="

make

echo "Starting test with automatic exit after 2 seconds..."

# Eseguiamo il programma e lo terminiamo automaticamente dopo 2 secondi
(sleep 2 && pkill -f "./cub3D") &

valgrind --leak-check=full --show-leak-kinds=all ./cub3D assets/map/valid.cub 2>&1 | \
grep -E "(still reachable|definitely lost|LEAK SUMMARY|ERROR SUMMARY|35 bytes|48 bytes)" | \
head -15

echo -e "\n🎯 Test Complete!"
