t9 = "22233344455566677778889999"
# 分别对应 abcdefghijklmnopqrstuvwxyz 这 26 个字母

def letter_digit(x):
    assert 'a' <= x and x <= 'z'
    return t9[ord(x)-ord('a')]

def word_code(words):
    return ''.join(map(letter_digit,words))

def predictive_text(dico):  # dico 是一个字典
    freq = {}   # freq[p] = 拥有前缀 p 的单词的总权重
    for words, weights in dico:
        prefix = ""
        for x in words:
            prefix += x
            if prefix in freq:
                freq[prefix] += weights
            else:
                freq[prefix] = weights

    # prop[s] = 输入 s 时要显示的前缀
    prop = {}
    for prefix in freq:
        code = word_code(prefix)
        if code not in prop or freq[prop[code]] < freq[prefix]:
            prop[code] = prefix
    return prop

def propose(prop, seq):
    if seq in prop:
        return prop[seq]
    else:
        return "None"

def run():
    
