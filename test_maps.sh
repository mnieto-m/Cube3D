#!/bin/bash

echo "======================================"
echo "PRUEBAS DE MAPS VALIDOS E INVALIDOS"
echo "======================================"

test_map() {
    local map=$1
    local description=$2
    echo ""
    echo "📋 Test: $description"
    echo "📁 Map: $map"
    echo "---"
    timeout 2 ./cub3D "$map" 2>&1 | grep -E "(Error|INVALID|llegue al final|NO:|SO:|Player)" | head -20
}

echo ""
echo "✅ MAPS QUE DEBERÍAN SER VÁLIDOS:"
test_map "maps/good/subject_map.cub" "Mapa completo válido"
test_map "maps/good/test_map.cub" "Mapa test simple"
test_map "maps/good/square_map.cub" "Mapa cuadrado"

echo ""
echo ""
echo "❌ MAPS QUE DEBERÍAN SER INVÁLIDOS:"
test_map "maps/bad/player_none.cub" "Sin jugador"
test_map "maps/bad/map_first.cub" "Mapa antes de config"
test_map "maps/bad/textures_missing.cub" "Texturas incompletas"
test_map "maps/bad/player_multiple.cub" "Jugador duplicado"
test_map "maps/bad/player_on_edge.cub" "Jugador en borde"
test_map "maps/bad/wall_none.cub" "Sin paredes"

echo ""
echo "======================================"
echo "RESUMEN: El programa ACEPTA todo"
echo "======================================"
