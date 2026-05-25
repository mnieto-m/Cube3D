#!/bin/bash

echo "╔══════════════════════════════════════════════════════════════════════════╗"
echo "║              TEST COMPLETO DE TODOS LOS MAPAS - cub3D                   ║"
echo "╚══════════════════════════════════════════════════════════════════════════╝"


# Detectar si la salida es una terminal
if [ -t 1 ]; then
    USE_COLOR=1
else
    USE_COLOR=0
fi

if [ "$USE_COLOR" -eq 1 ]; then
    GREEN='\033[0;32m'
    RED='\033[0;31m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    NC='\033[0m'
    PASS_ICON="✅"
    FAIL_ICON="❌"
    WARN_ICON="⚠️"
    PARTY_ICON="🎉"
else
    GREEN=''
    RED=''
    YELLOW=''
    BLUE=''
    NC=''
    PASS_ICON="PASS"
    FAIL_ICON="FAIL"
    WARN_ICON="WARN"
    PARTY_ICON="ALL TESTS PASSED"
fi

# Contadores
total=0
passed=0
failed=0

test_map() {
    local map=$1
    local description=$2
    local should_pass=$3
    
    total=$((total + 1))
    
    # Ejecutar el test
    output=$(timeout 2 ./cub3D "$map" 2>&1)
    exit_code=$?
    
    # Determinar si pasó o no
    is_valid=0
    if echo "$output" | grep -q "INVALID\|^Error\|Player not found\|File is empty\|No map content\|TEXTURES:\|Configuration line\|duplicado"; then
        is_valid=0
    else
        is_valid=1
    fi
    
    # Comparar con lo esperado
    if [ "$should_pass" = "PASS" ]; then
        expected=1
    else
        expected=0
    fi
    
    if [ $is_valid -eq $expected ]; then
        passed=$((passed + 1))
        if [ "$should_pass" = "PASS" ]; then
            printf "%b%s%b | %s\n" "$GREEN" "$PASS_ICON" "$NC" "$description"
        else
            printf "%b%s%b | %s\n" "$GREEN" "$PASS_ICON" "$NC" "$description"
        fi
    else
        failed=$((failed + 1))
        if [ "$should_pass" = "PASS" ]; then
            printf "%b%s%b | %s (debería aceptarse)\n" "$RED" "$FAIL_ICON" "$NC" "$description"
            echo "     Output: $(echo "$output" | grep -E 'INVALID|Error' | head -1)"
        else
            printf "%b%s%b | %s (debería rechazarse)\n" "$RED" "$FAIL_ICON" "$NC" "$description"
            echo "     Output: Sin error detectado"
        fi
    fi
}

echo ""
echo "════════════════════════════════════════════════════════════════════════════"
echo "✅ MAPAS VÁLIDOS (maps/good/) - Deben ser ACEPTADOS"
echo "════════════════════════════════════════════════════════════════════════════"

test_map "maps/good/subject_map.cub" "subject_map.cub - Mapa complejo válido" "PASS"
test_map "maps/good/test_map.cub" "test_map.cub - Mapa de prueba simple" "PASS"
test_map "maps/good/test_map_hole.cub" "test_map_hole.cub - Mapa con agujero" "PASS"
test_map "maps/good/square_map.cub" "square_map.cub - Mapa cuadrado" "PASS"
test_map "maps/good/matrix.cub" "matrix.cub - Mapa matrix" "PASS"
test_map "maps/good/cheese_maze.cub" "cheese_maze.cub - Laberinto" "PASS"
test_map "maps/good/creepy.cub" "creepy.cub - Mapa creepy" "PASS"
test_map "maps/good/dungeon.cub" "dungeon.cub - Mazmorra" "PASS"
test_map "maps/good/library.cub" "library.cub - Biblioteca" "PASS"
test_map "maps/good/sad_face.cub" "sad_face.cub - Cara triste" "PASS"
test_map "maps/good/test_pos_bottom.cub" "test_pos_bottom.cub - Jugador abajo" "PASS"
test_map "maps/good/test_pos_left.cub" "test_pos_left.cub - Jugador izquierda" "PASS"
test_map "maps/good/test_pos_right.cub" "test_pos_right.cub - Jugador derecha" "PASS"
test_map "maps/good/test_pos_top.cub" "test_pos_top.cub - Jugador arriba" "PASS"
test_map "maps/good/test_textures.cub" "test_textures.cub - Texturas" "PASS"
test_map "maps/good/test_whitespace.cub" "test_whitespace.cub - Con espacios" "PASS"
test_map "maps/good/works.cub" "works.cub - Funciona" "PASS"

echo ""
echo "════════════════════════════════════════════════════════════════════════════"
echo "❌ MAPAS INVÁLIDOS (maps/bad/) - Deben ser RECHAZADOS"
echo "════════════════════════════════════════════════════════════════════════════"

test_map "maps/bad/empty.cub" "empty.cub - Archivo vacío" "FAIL"
test_map "maps/bad/player_none.cub" "player_none.cub - Sin jugador" "FAIL"
test_map "maps/bad/player_multiple.cub" "player_multiple.cub - Jugador duplicado" "FAIL"
test_map "maps/bad/player_on_edge.cub" "player_on_edge.cub - Jugador en borde" "FAIL"
test_map "maps/bad/map_first.cub" "map_first.cub - Mapa antes de config" "FAIL"
test_map "maps/bad/map_middle.cub" "map_middle.cub - Mapa en medio de config" "FAIL"
test_map "maps/bad/map_missing.cub" "map_missing.cub - Mapa faltante" "FAIL"
test_map "maps/bad/map_only.cub" "map_only.cub - Solo mapa sin config" "FAIL"
test_map "maps/bad/map_too_small.cub" "map_too_small.cub - Mapa muy pequeño" "FAIL"
test_map "maps/bad/wall_none.cub" "wall_none.cub - Sin muros" "FAIL"
test_map "maps/bad/wall_hole_north.cub" "wall_hole_north.cub - Agujero norte" "FAIL"
test_map "maps/bad/wall_hole_south.cub" "wall_hole_south.cub - Agujero sur" "FAIL"
test_map "maps/bad/wall_hole_east.cub" "wall_hole_east.cub - Agujero este" "FAIL"
test_map "maps/bad/wall_hole_west.cub" "wall_hole_west.cub - Agujero oeste" "FAIL"
test_map "maps/bad/textures_missing.cub" "textures_missing.cub - Falta textura" "FAIL"
test_map "maps/bad/textures_none.cub" "textures_none.cub - Sin texturas" "FAIL"
test_map "maps/bad/textures_duplicates.cub" "textures_duplicates.cub - Texturas duplicadas" "FAIL"
test_map "maps/bad/textures_invalid.cub" "textures_invalid.cub - Texturas inválidas" "FAIL"
test_map "maps/bad/textures_not_xpm.cub" "textures_not_xpm.cub - No son XPM" "FAIL"
test_map "maps/bad/textures_dir.cub" "textures_dir.cub - Texturas son directorio" "FAIL"
test_map "maps/bad/textures_forbidden.cub" "textures_forbidden.cub - Texturas prohibidas" "FAIL"
test_map "maps/bad/color_none.cub" "color_none.cub - Sin colores" "FAIL"
test_map "maps/bad/color_missing.cub" "color_missing.cub - Color faltante" "FAIL"
test_map "maps/bad/color_missing_floor_rgb.cub" "color_missing_floor_rgb.cub - RGB piso incompleto" "FAIL"
test_map "maps/bad/color_missing_ceiling_rgb.cub" "color_missing_ceiling_rgb.cub - RGB techo incompleto" "FAIL"
test_map "maps/bad/color_invalid_rgb.cub" "color_invalid_rgb.cub - RGB inválido" "FAIL"
test_map "maps/bad/file_letter_end.cub" "file_letter_end.cub - Extensión incorrecto" "FAIL"
test_map "maps/bad/filetype_wrong.buc" "filetype_wrong.buc - Tipo de archivo incorrecto" "FAIL"
test_map "maps/bad/forbidden.cub" "forbidden.cub - Contenido prohibido" "FAIL"

echo ""
echo "════════════════════════════════════════════════════════════════════════════"
echo "📊 RESUMEN FINAL"
echo "════════════════════════════════════════════════════════════════════════════"
echo ""
printf "Total de mapas testeados: %b%d%b\n" "$BLUE" "$total" "$NC"
printf "%s Pasados: %b%d%b\n" "$PASS_ICON" "$GREEN" "$passed" "$NC"
printf "%s Fallidos: %b%d%b\n" "$FAIL_ICON" "$RED" "$failed" "$NC"
echo ""


percentage=$((passed * 100 / total))
printf "Tasa de éxito: %b%d%%%b (%d/%d)\n" "$YELLOW" "$percentage" "$NC" "$passed" "$total"

if [ $failed -eq 0 ]; then
    echo ""
    printf "%b%s%b\n" "$GREEN" "$PARTY_ICON" "$NC"
    exit 0
else
    echo ""
    printf "%b%s  Hay %d test(s) que fallaron%b\n" "$RED" "$WARN_ICON" "$failed" "$NC"
    exit 1
fi
