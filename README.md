# 🗃 Containers

Reimplementing some stl containers

## 🗄️ Containers:

- [Vector]
- [Deque]
- [Stack]
- [Map]
- [Set]

## 🖇️ Features:
- Iterators
- Iterator traits
- enable_if
- Type traits

## 🪴 Implementation:
`Deque` is implemented as a [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer)  
`Map` and `Set` are both implemented as a [red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)

## 📊 Bench mark results:
I ran benchmarks on all my containers with my own tester which can be found [here](https://github.com/K1ngmar/Container-Tester)

### Vector:
![img](./vector/vector_benchmark.png)

### Deque:
![img](./deque/deque_benchmark.png)

### Map:
![img](./map/map_benchmark.png)

### Set:
![img](./Set/Set_benchmark.png)
