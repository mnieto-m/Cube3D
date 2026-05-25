#!/bin/bash
echo "════════════════════════════════════════════"
echo "      PRUEBAS DE VALIDACIÓN DE MAPS"
echo "════════════════════════════════════════════"

test_map() {
    local map=$1
    local desc=$2
    local expected=$3
    echo ""
    echo "📋 $desc"
    echo "   Map: $map"
    output=$(timeout 2 ./cub3D "$map" 2>&1 | grep -E "(INVALID|llegue|Player|Error)" | head -1)
    if echo "$output" | grep -q "INVALID\|Error"; then
        result="❌ RECHAZADO"
    else
        result="✅ ACEPTADO"
    fi
    echo "   Resultado: $result"
    echo "   Output: $output"
    if [ "$expected" = "REJECT" ] && echo "$output" | grep -q "INVALID\|Error"; then
        echo "   ✅ CORRECTO"
    elif [ "$expected" = "ACCEPT" ] && ! echo "$output" | grep -q "INVALID\|Error"; then
        echo "   ✅ CORRECTO"
    else
        echo "   ❌ INCORRECTO"
    fi
}

echo ""
echo "✅ MAPS VÁLIDOS (deben aceptarse):"
echo "══════════════════════════════════"
test_map "maps/good/subject_map.cub" "Subject map - válido" "ACCEPT"
test_map "maps/good/test_map.cub" "Test map - válido" "ACCEPT"
test_map "maps/good/square_map.cub" "Square map - válido" "ACCEPT"

echo ""
echo ""
echo "❌ MAPS INVÁLIDOS (deben rechazarse):"
echo "═════════════════════════════════════"
test_map "maps/bad/player_none.cub" "Sin jugador" "REJECT"
test_map "maps/bad/textures_missing.cub" "Falta textura NO" "REJECT"
test_map "maps/bad/player_multiple.cub" "Jugador duplicado" "REJECT"
test_map "maps/bad/map_first.cub" "Mapa primero (no config)" "REJECT"

echo ""
echo "════════════════════════════════════════════"
echo "      FIN DE PRUEBAS"
echo "════════════════════════════════════════════"
