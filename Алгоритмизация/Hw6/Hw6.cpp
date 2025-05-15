#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>
#include <set>
#include <functional>

using namespace std;
using namespace sf;

const int GRID_SIZE = 10; // Размер поля NxN
const int CELL_SIZE = 50;  // Размер одной ячейки в пикселях
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;

// Типы ячеек
enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    PATH,
    VISITED,
    QUEUED
};

// Дополнительные цвета
Color Orange(229, 135, 34, 255);
Color Purple(90, 34, 139, 255);

// Структура для представления ячейки
struct Cell {
    int x, y;
    CellType type;
    int f, g, h; // Для алгоритма A*
    Cell* parent;

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), parent(nullptr) {}

    void updateF() {
        f = g + h;
    }

    // Перезагрузка оператора == для сравнения ячеек
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }

    

};

// Добавляем оператор сравнения для Cell (необходим для priority_queue)
    bool operator>(const Cell& a, const Cell& b) {
        return a.f > b.f;
    }

// Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int x, int y) {
    return (x < GRID_SIZE) and (y < GRID_SIZE) and (x >= 0) and (y >= 0);
}

// Обновляет список соседей, в которые можно перейти (не препятствия).
vector<Cell*> get_neighbors(vector<vector<Cell>>& grid, Cell* cell) {
    vector<Cell*> neighbors;
    for (auto [dx, dy] : vector<pair<int, int>>{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }) {
        int nx = cell->x + dx;
        int ny = cell->y + dy;
        if (isValid(nx, ny) and (grid[nx][ny].type != OBSTACLE)) {
            neighbors.push_back(&grid[nx][ny]);
        }
    }
    return neighbors;
}

// Задают тип и цвет ячейки.
//make_start()
//make_end()
//make_barrier()

// Сетка создаётся функцией make_grid(), которая возвращает список списков объектов Cell
vector<vector<Cell>> make_grid() {
    vector<vector<Cell>> grid;
    int start_x = 0;
    int start_y = 0;
    int end_x = 9;
    int end_y = 9;
    vector<vector<int>> gridtempl = {
            {0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 0}
        };
    for (int x = 0; x < GRID_SIZE; x++) {
        vector<Cell> row;
        for (int y = 0; y < GRID_SIZE; y++) {
            Cell cell(x, y);
            cell.h = abs(x - end_x) + abs(y - end_y);
            cell.updateF();
            if (gridtempl[y][x]) cell.type = OBSTACLE;
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    Cell* start = &grid[start_x][start_y];
    Cell* end = &grid[end_x][end_y];
    start->type = START;
    start->g = 0;
    end->type = END;
    
    pair<Cell*, Cell*> p(start, end);

    return grid;
}


pair<vector<vector<Cell>>, pair<pair<int, int>, pair<int, int>>> make_random_grid() {
    vector<vector<Cell>> grid;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, GRID_SIZE - 1);

    // Генерация старта и финиша
    int start_x = distrib(gen);
    int start_y = distrib(gen);
    int end_x = distrib(gen);
    int end_y = distrib(gen);

    // Убедимся, что старт и финиш не совпадают
    while (start_x == end_x && start_y == end_y) {
        end_x = distrib(gen);
        end_y = distrib(gen);
    }

    // Создаем сетку
    for (int x = 0; x < GRID_SIZE; x++) {
        vector<Cell> row;
        for (int y = 0; y < GRID_SIZE; y++) {
            Cell cell(x, y);
            cell.h = abs(x - end_x) + abs(y - end_y);
            cell.updateF();
            row.push_back(cell);
        }
        grid.push_back(row);
    }

    // Устанавливаем старт и финиш
    Cell* start = &grid[start_x][start_y];
    Cell* end = &grid[end_x][end_y];
    start->type = START;
    start->g = 0;
    end->type = END;

    // Генерация препятствий (20% от площади)
    int obstacle_count = static_cast<int>(GRID_SIZE * GRID_SIZE * 0.2);
    int obstacles_placed = 0;

    while (obstacles_placed < obstacle_count) {
        int x = distrib(gen);
        int y = distrib(gen);
        Cell* cell = &grid[x][y];

        // Проверяем, что это не старт и не финиш
        if (cell->type == EMPTY) {
            cell->type = OBSTACLE;
            obstacles_placed++;
        }
    }

    return make_pair(grid, make_pair(make_pair(start_x, start_y), make_pair(end_x, end_y)));
}


//Функция draw_grid(win, grid) отрисовывает ячейки и линии сетки.
void draw_grid(RenderWindow& window, vector<vector<Cell>>& grid) {
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            switch (grid[x][y].type) {
            case EMPTY: cell.setFillColor(Color::White); break;
            case OBSTACLE: cell.setFillColor(Color::Black); break;
            case START: cell.setFillColor(Orange); break;
            case END: cell.setFillColor(Color::Cyan); break;
            case PATH: cell.setFillColor(Purple); break;
            case VISITED: cell.setFillColor(Color::Red); break;
            case QUEUED: cell.setFillColor(Color::Green); break;
            }
            cell.setOutlineColor(Color::Black);
            cell.setOutlineThickness(1);
            window.draw(cell);
        }
    }
}


vector<pair<int, int>> a_star(vector<vector<Cell>>& grid, Cell* start, Cell* goal) {
    // Приоритетная очередь для открытого списка, элемент с наименьшим f всегда на вершине
    priority_queue<Cell*, vector<Cell*>, function<bool(Cell*, Cell*)>> open_list(
        [](Cell* a, Cell* b) { return a->f > b->f; }
    );

    set<pair<int, int>> closed_list;

    // Инициализация начальной точки
    start->g = 0;
    start->h = heuristic(*start, *goal);
    start->updateF();
    open_list.push(start);

    // Пока открытый список не пуст, обновляем данные о вершинах
    while (!open_list.empty()) {
        // Берется вершина с min F и удалется из списка
        Cell* current = open_list.top();
        open_list.pop();

        // Если достигли цели, восстанавливаем путь
        if (current->x == goal->x && current->y == goal->y) {
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.emplace_back(current->x, current->y);

                // Меняем тип ячейки на PATH (кроме START и END)
                if (current->type != START && current->type != END) {
                    grid[current->x][current->y].type = PATH;
                }
                current = current->parent;;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        // Текущая вершина - посещенная - помещается в закрытый список, чтобы больше к ней не возвращаться
        closed_list.insert({ current->x, current->y });

        if (grid[current->x][current->y].type != START && grid[current->x][current->y].type != END) {
            grid[current->x][current->y].type = VISITED; // Для отрисовки  посещенной красным
        }
        

        cout << "(" << current->x
            << ", " << current->y
            << ")  " << current->f << " "
            << "g: " << current->g << "  "
            << "h: " << current->h << endl;

        // Проверяем всех соседей
        for (auto [dx, dy] : vector<pair<int, int>>{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }) {
            int nx = current->x + dx;
            int ny = current->y + dy;
            
            // Проверка что не вышли за пределы матрицы
            if (!isValid(nx, ny)) continue;
                Cell* neighbor = &grid[nx][ny];

                // Пропускаем препятствия и уже посещённые клетки
                if (neighbor->type == OBSTACLE || closed_list.count({ nx, ny })) {
                    continue;
                }

                // Расчет g, если пойдем в эту клетку следующим шагом
                int tentative_g = current->g + 1;
                // Если соседняя клетка уже находится в открытом списке,
                // сравниваем значение G у неё и у текущей проверяемой клетки :
                // если прежнее значение G меньше нового, то ничего не делаем;
                // если новое значение G меньше, то обновляем G и меняем родителя на текущую клетку.
                if (tentative_g < neighbor->g || neighbor->g == 0) {
                    // Запись родительской вершины для возможности восстановить путь и обновление g, h, f
                    neighbor->parent = current;
                    neighbor->g = tentative_g;
                    neighbor->h = heuristic(*neighbor, *goal);
                    neighbor->updateF();
                    // Добавление в открытый список чтобы потом посетить эту клетку
                    open_list.push(neighbor);
                    if (neighbor->type != END ) neighbor->type = QUEUED;
                }
        }
    }

    return {}; // Путь не найден
}


int main() {
    // Загрузка шрифта для вывода текста
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  // Путь к файлу шрифта
        return EXIT_FAILURE;
    }

    // Настройка текста для вывода статуса
    sf::Text statusText;
    statusText.setFont(font);

    vector<vector<Cell>> grid;
    grid = make_grid();
    Cell* start = &grid[0][0];
    Cell* goal = &grid[9][9];

    //Создание окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE,  WINDOW_SIZE), L"Маршрут");
    // Основной цикл окна
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed)
               window.close();
           if (event.type == Event::KeyPressed) {
               if (event.key.scancode == Keyboard::Scan::Space) { // Запуск алгоритма A* 
                   auto path = a_star(grid, start, goal);
              }
               
               if (event.key.scancode == Keyboard::Scan::R) { // Генерация нового случайного поля
                    auto p = make_random_grid();
                    grid = p.first;
                    int start_x = p.second.first.first;
                    int start_y = p.second.first.second;
                    int end_x = p.second.second.first;
                    int end_y = p.second.second.second;
                    start = &grid[start_x][start_y];
                    goal = &grid[end_x][end_y];
               }

           }
        }
        window.clear();
        draw_grid(window, grid);
        window.display();
    }
    return 0;
}