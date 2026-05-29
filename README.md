Sobre el proyecto:

Esta versión contiene estas características avanzadas:
- Minimapa dinámico
- Gestión robusta del archivo .cub
- Texturas personalizadas
- Eventos de teclado y ratón integrados con la librería mlx42.
- Raycasting con DDA optimizado, inspirado en el videojuego Wolfenstein 3D (1992)
- efecto de profundidad con oscurecimiento de paredes lejanas

Objetivos del proyecto:

Compilación y ejecución:

Controles:

Estructura general del motor:

Formato del archivo .cub:

Sistema de raycasting:

principales archivos para el raycasting:

exec.c >
render.c >
orientation.c > así sabemos si el rayo chocó en el plano X o Y, y pared vertical u horizontal, y así determinamos la textura de la pared correspondiente según la orientación
draw.c > 

Estructura del proyecto:


