import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from matplotlib.patches import Circle


class StateRepresentor:
    def __init__(self, x_range, y_range):
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim(0, x_range)
        self.ax.set_ylim(0, y_range)

        self.ax.set_aspect('equal')
        self.ax.set_xlabel('X-axis')
        self.ax.set_ylabel('Y-axis')
        self.ax.set_title('AISLE')

    def draw_rectangle(self, name, x, y, width, height, mode=None):

        rectangle = Rectangle((x-width/2, y-height/2), width, height, edgecolor='black', facecolor='gray')
        self.ax.add_patch(rectangle)

        text_x = x
        text_y = y
        number = name
        self.ax.text(text_x, text_y, str(number), ha='center', va='center')

    def draw_potential_points(self, potential_points):
        for point in potential_points:
            x = point.x
            y = point.y
            circle = Circle((x, y), 0.5, facecolor='red')
            self.ax.add_patch(circle)


sr = StateRepresentor(20, 50)
sr.draw_rectangle('1', 2, 4, 4, 8)
sr.draw_rectangle('2', 19, 3, 2, 6)

plt.show()

