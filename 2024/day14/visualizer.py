import tkinter as tk
import time

WIDTH, HEIGHT = 101, 103
WIN_WIDTH, WIN_HEIGHT = 800, 600

maps = []
current_map = 0
 
def display_map(canvas: tk.Canvas, time: str, map: list[str]):
    canvas.delete("all");
    offsetX = WIN_WIDTH//2 - WIDTH*5//2;
    offsetY = WIN_HEIGHT//2 - HEIGHT*5//2;
    for i in range(HEIGHT):
        for j in range(WIDTH):
            x = j*5 + offsetX;
            y = i*5 + offsetY;
            if map[i][j] == "#":
                canvas.create_rectangle(x, y, x+5, y+5, fill="black", outline="black");
    canvas.create_text(20, 10, anchor="nw", text=time, font=("Arial", 13));
    canvas.pack();


def next_map(canvas: tk.Canvas, window: tk.Tk, diff=+1):
    global current_map, maps;
    current_map = (current_map+diff)%len(maps);
    info = maps[current_map];
    display_map(canvas, info[0], info[1]);
    window.update();


def main(file: str):
    global maps;
    maps = []
    with open(file, "r") as f:
        lines = f.readlines();
        print("Loading maps..., est: ", len(lines)/(HEIGHT+1));
        while (len(lines) > 0):
            info = lines.pop(0).strip();
            map = lines[0:HEIGHT];
            maps.append((info, map));
            lines = lines[HEIGHT:];
            if (len(lines) % (500*(HEIGHT+1)) == 0):
                print(f"{len(maps)}/{(int)(len(lines)/(HEIGHT+1))} maps loaded");
    print("Maps loaded");

    window = tk.Tk();
    window.geometry(f"{WIN_WIDTH}x{WIN_HEIGHT}");
    window.resizable(False, False);
    window.title("Easteregg hunter");

    canvas = tk.Canvas(window, width=800, height=600);
    window.bind('<Right>', lambda _: next_map(canvas, window, +1));
    window.bind('<Left>' , lambda _: next_map(canvas, window, -1));
    window.mainloop();

if __name__ == "__main__":
    main("b.out");
