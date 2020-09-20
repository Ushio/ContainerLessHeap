## ContainerLessHeap Heap

- leave memory operation to user
- no template<>

### Build

```
premake5 vs2019
```

### Code

```
std::priority_queue<int, std::vector<int>, std::greater<int>> pQue;
int heapKeys[1000];
int heapCount = 0;

int N = rand() % 1000;

for (int i = 0; i < N; ++i)
{
    int v = rand();
    heapKeys[heapCount++] = v;
    pQue.push(v);

    for (HeapSwapIterator it = heapPushBegin(heapCount); !heapPushIsEnd(heapKeys, it); it = heapPushNext(it))
    {
        std::swap(heapKeys[it.itemC], heapKeys[it.itemP]);
    }
}
for (int i = 0; i < N; ++i)
{
    int v = heapKeys[0];
    heapKeys[0] = heapKeys[--heapCount];
    for (HeapSwapIterator it = heapPopBegin(heapKeys, heapCount); !heapPopIsEnd(heapKeys, heapCount, it); it = heapPopNext(heapKeys, heapCount, it))
    {
        std::swap(heapKeys[it.itemC], heapKeys[it.itemP]);
    }

    if (pQue.top() != v)
    {
        printf("failure: %d != %d\n", pQue.top(), v);
    }
    pQue.pop();
}
```
