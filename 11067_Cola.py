while True:
    try:
        n = int(input())
        print(int(n * 1.5))
    except EOFError: # 可以直接處理EOF
        break  # 沒測資了就跳出迴圈