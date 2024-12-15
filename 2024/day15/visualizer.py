import sys
import tkinter as tk
import time

WIN_WIDTH, WIN_HEIGHT = 800, 600
UNIT = 10
MAPS_TO_LOAD = 20000

BOT_COLOR = '#00a6ff'
WALL_COLOR = 'black'
OBSTACLE_COLOR = '#ff4760'

current_map = 0

def load_input(filename: str):
    maps: list[list[str]] = []
    with open(filename, 'r') as f:
        lines = f.readlines()
        _, h = map(int, lines.pop(0).split())
        total_maps = (int)(len(lines)/(h+1))
        print("Loading maps..., est: ", total_maps)
        while len(lines) > 0:
            if (len(maps) % 100 == 0 and len(maps) != 0):
                print(f"{len(maps)}/{total_maps} maps loaded")
                if (len(maps) % MAPS_TO_LOAD == 0):
                    break
            i: str = lines.pop(0)
            if (i.startswith('move')):
                maps.append([line.strip() for line in lines[:h]])
            else:
                break
            lines = lines[h+1:]
    print("Maps loaded")
    return maps


def display_map(canvas: tk.Canvas, map: list[str]):
    canvas.delete('all')
    offset_x = (WIN_WIDTH - len(map[0]) * UNIT) // 2
    offset_y = (WIN_HEIGHT - len(map) * UNIT) // 2
    for i in range(len(map)):
        for j in range(len(map[0])):
            x = j * UNIT + offset_x
            y = i * UNIT + offset_y
            if map[i][j] == '#':
                canvas.create_rectangle(x, y, x + UNIT, y + UNIT, fill=WALL_COLOR, outline=WALL_COLOR)
            elif map[i][j] == '@':
                canvas.create_rectangle(x, y, x + UNIT, y + UNIT, fill=BOT_COLOR, outline=BOT_COLOR)
            elif map[i][j] == '[':
                canvas.create_rectangle(x, y, x + 2*UNIT, y + UNIT, fill=OBSTACLE_COLOR, outline='black')
    canvas.pack()


def update(maps: list[list[str]], canvas: tk.Canvas, window: tk.Tk):
    global current_map
    current_map = (current_map + 1) % len(maps)
    display_map(canvas, maps[current_map])
    window.update()
    window.after(10, update, maps, canvas, window)


def main(filename: str):
    maps = load_input(filename)
    
    window = tk.Tk()
    window.geometry(f'{WIN_WIDTH}x{WIN_HEIGHT}')
    window.resizable(False, False)
    window.title('Visualizer')

    canvas = tk.Canvas(window, width=800, height=600)
    window.after(10, update, maps, canvas, window)
    window.mainloop()


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python visualizer.py <filename> [max_maps]')
        sys.exit(1)
    if len(sys.argv) == 3:
        MAPS_TO_LOAD = int(sys.argv[2])
    main(sys.argv[1])
