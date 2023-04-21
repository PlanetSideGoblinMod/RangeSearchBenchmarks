# 2D Range Search Benchmarks


## Range Tree with Fractional Cascading


O(logn) query, O(nlogn) build time. This is an edited fork of an implementation by github.com/luoyuanlab


### Random Case: Search Distance = 500 out of 65535
![](randomcase.png)


### Worst Case: Search Distance = 50000 out of 65535
![](worstcase.png)


# TODO:
Replace sort algorithm in Range Tree with pdqsort or vqsort
