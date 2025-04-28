# Doom Clone

Простая реализация движка в стиле Doom на C++ с использованием OpenGL и SDL2.

## Зависимости

- CMake (>= 3.10)
- C++17 компилятор
- SDL2
- SDL2_image
- SDL2_mixer
- OpenGL
- Python 3 (для генерации текстур)
- NumPy
- Pillow (Python Imaging Library)

## Установка зависимостей на Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install cmake build-essential libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev python3 python3-pip
pip3 install numpy pillow
```

## Сборка

```bash
mkdir build
cd build
cmake ..
make
```

## Генерация текстур

```bash
python3 generate_textures.py
```

## Запуск

```bash
./doom_clone
```

## Управление

- W/S - движение вперед/назад
- A/D - поворот влево/вправо
- ESC - выход из игры

## Структура проекта

- `src/` - исходный код
- `include/` - заголовочные файлы
- `assets/` - ресурсы игры
  - `textures/` - текстуры
  - `sounds/` - звуковые эффекты
  - `maps/` - карты уровней # doom
