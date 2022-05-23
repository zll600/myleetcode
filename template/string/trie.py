class TrieNode:
    def __init__(self):
        self.is_word = False
        self.children = {c: None for c in list("abcdefghijklmnopqrstuvwxyz")}

# 这里递归的插入
def add(trie, word, idx = 0):
    if trie is None:
        # 生成一个新节点
        trie = TrieNode()
    if idx == len(word):
        # 单词遍历结束，给这个节点加个标志
        trie.is_word = True
    else:
        # 需要创建一个子节点
        trie.children[word[idx]] = add(trie.children[word[idx]], word, idx + 1)
    return trie

# 初始化一棵 前缀树
def Trie(words):
    trie = None
    for word in words:
        trie = add(trie, word)
    return trie

# 拼写纠正
def spell_check(trie, word):
    assert trie is not None
    dist = 0
    while True:
        c = search(trie, dist, word)  # 尝试用越来越多的距离来查找
        if c is not None:
            return c
        dist += 1

# 递归查找
def search(trie, dist, word, idx = 0):
    if idx == len(word):
        # 如果 w 遍历结束
        if trie is not None and trie.is_word and dist == 0:
            # 没有错误
            return ''
        else:
            return None

    if trie is None:
        return None
    # 继续匹配
    f = search(trie.children[word[idx]], dist, word, idx + 1)   # 相关
    if f is not None:
        # 如果出现错误
        return word[idx] + f

    if dist == 0:
        return None
    for c in list("abcdefghijklmnopqrstuvwxyz"):
        f = search(trie.children[c], dist - 1, word, idx)  # 插入
        if f is not None:
            # 如果出现错误
            return c + f

        f = search(trie.children[c], dist - 1, word, idx + 1) # 替换
        if f is not None:
            # 如果出现错误
            return c + f

    return search(trie, dist - 1, word, idx + 1)

def run():
    trie = Trie('port')
    print(spell_check(trie, 'porr'))

if __name__ == '__main__':
    run()
