flipfront <- function(x, n) {
    if(n == 1) return(x)
    for( i in 1:floor(n/2) ) {
        x[i] <- bitwXor(x[i], x[n - i + 1])
        x[n - i + 1] <- bitwXor(x[i], x[n - i + 1])
        x[i] <- bitwXor(x[i], x[n - i + 1])
    }
    return(x)
}

pancakeSort <- function(x) {
    for(i in length(x):2){
        n <- which(x[1:i] == max(x[1:i]))[1]
        x <- flipfront(x, n)
        x <- flipfront(x, i)
    }
    return(x)
}
