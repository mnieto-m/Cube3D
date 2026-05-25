#!/bin/bash
echo "════════════════════════════════════════════"
echo "        PRUEBAS FINALES DE VALIDACIÓN"
echo "════════════════════════════════════════════"

test_map() {
    local map=$1
    local desc=$2
    echo ""
    echo "📋 $desc"
    output=$(timeout 2 ./cub3D "$map" 2>&1 | grep -E "(INVALID|llegue)" | head -1)
    if echo "$output" | grep -q "INVALID"; then
        echo "   ❌ RECHAZADO: $output"
    else
        echo "   ✅ ACEPTADO"
    fi
}

echo ""
echo "✅ MAPS VÁLIDOS:"
test_map "maps/good/subject_map.cub" "Subject map"
test_map "maps/good/test_map.cub" "Test map"
test_map "maps/good/square_map.cub" "Square map"

echo ""
echo "❌ MAPS INVÁLIDOS:"
test_map "maps/bad/empty.cub" "Archivo vacío"
test_map "maps/bad/player_none.cub" "Sin jugador"
test_map "maps/bad/textures_missing.cub" "Falta textura"
test_map "maps/bad/player_multiple.cub" "Jugador duplicado"
test_map "maps/bad/map_first.cub" "Mapa primero"

echo ""
echo "════════════════════════════════════════════"
