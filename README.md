# 2D Range Search Benchmarks


## Range Tree with Fractional Cascading (forked implementation from github.com/luoyuanlab)


O(logn) query, O(nlogn) build time


### Random Case: Search Distance = 500 out of 65535
![](randomcase.png)


### Worst Case: Search Distance = 50000 out of 65535
![](worstcase.png)


# TODO:
Replace sort algorithm in Range Tree with pdqsort or vqsort
