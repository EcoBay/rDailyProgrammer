f <- function(x){
    ctr <- 0
    for(i in 0:log10(x)){
        ctr <- ctr + ceiling(floor(x / 10 ^ i) / 10) * 10 ^ i
        if( floor(x / 10 ^ i) %% 10 == 1){
            ctr <- ctr - ( 10 ^ i - 1 - x %% 10 ^ i )
        }
    }
    return(ctr)
}

solutions <- function(){
    s <- list()
    i <- 1
    while (i < 1e11) {
        a <- f(i)
        if( a == i ) s <- c(s, i)
        i <- i + 1 + if ( a != i) floor(abs(a - i) / (log10(i) + 2)) else 0
    }
    return(s)
}

challenge <- Reduce(`+`,solutions())
