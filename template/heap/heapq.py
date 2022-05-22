class OurHeap:
    def __init__(self, items):
        self.n = 0
        self.heap = [None]
        self.rank = {}
        for val in items:
            self.push(val)

    def __len__(self):
        return len(self.heap) - 1

    def push(self, val):
       assert val not in self.rank
       idx = len(self.heap)
       self.heap.append(val)  # 添加一个新的叶子节点
       self.rank[val] = idx
       self.up(idx)       # 保持堆排序

    def pop(self):
        root = self.heap[1]
        del self.rank[root]
        x = self.heap.pop()     # 移除最后一个叶子节点
        if self:                # 堆非空
            self.heap[1] = x    # 移动到根节点
            self.rank[x] = 1
            self.down(1)        # 保持堆有序

        return root

    def up(self, idx):
        val = self.heap[idx]
        while idx > 1 and val < self.heap[idx // 2]:
            self.heap[idx] = self.heap[idx // 2]
            self.rank[self.heap[idx // 2]] = idx
            idx //= 2

        self.heap[idx] = val    # 找到了插入点
        self.rank[val] = idx

    def down(self, idx):
        val = self.heap[idx]
        n = len(self.heap)
        while True:
            left = 2 * idx  # 在二叉树中下降
            right = left + 1
            if right < n and \
                self.heap[right] < val and self.heap[right] < self.heap[left]:
                self.heap[idx] = self.heap[right]
                self.rank[self.heap[right]] = idx   # 提升右侧子节点
                idx = right
            elif left < n and self.heap[left] < val:
                self.heap[idx] = self.heap[left]    # 提升左侧子节点
                self.rank[self.heap[left]] = idx
                idx = left
            else:
                self.heap[idx] = val    # 找到了插入元素
                self.rank[val] = idx
                return

    def update(self, old, new):
        idx = self.rank[old]
        del self.rank[old]
        self.heap[idx] = new
        self.rank[new] = idx
        if old < new:
            self.down(idx)
        else:
            self.up(idx)

if __name__ == "__main__":
    item = [6, 7, 8, 9]
    hp = OurHeap(item)
    hp.push(1)
    hp.push(4)
    hp.push(5)

    print(f'{hp.pop()}')
    print(f'{hp.pop()}')
    print(f'{hp.pop()}')
    print(f'{hp.pop()}')

