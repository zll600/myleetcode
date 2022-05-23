'''
这个算法的思路就是，计算每个单词的签名，如果两个单词可以得到相同的签名，，当前仅当他们互为易位异构词，

这个签名就是包含了相同字母的另一个单词，这里的处理方法就是，将所有字母按照顺序排列后得到的
'''

def anagrams(word):
    w = list(set(word))    # 删除重复项
    d = {}      # 保存有同样签名的单词

    for i in range(len(w)):
        s = ''.join(sorted(w[i]))   # 签名
        if s in d:
            d[s].append(i)
        else:
            d[s] = [i]
        
    # -- 提取易位异构词
    reponse = []
    for s in d:
        if len(d[s]) > 1:
            reponse.append([w[i] for i in d[s]])
    return reponse

def run():
    word = [ "une", "nue", "marche", "charme", "chien", "chine"]
    print(anagrams(word))

if __name__ == "__main__":
    run()
