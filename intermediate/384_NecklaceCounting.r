coprime <- function(a, b){
    if( a <= 1) return (a)
    if(a < b){
        a <- a + b
        b <- a - b
        a <- a - b
    }
    repeat{
        r <- a %% b
        a <- b
        b <- r
        if(r <= 1){ return(r) }
    }
}

phi <- function(a){
    if( a <= 1) return (a)
    r <- 0
    for( i in 0:(a-1)){
        r <- r + coprime(i, a)
    }
    return(r)
}

necklaces <- function(k, n){
    s <- 0
    for(i in 1:n){
        if(n %% i == 0){
            s <- s + phi(i) * k ^ (n / i)
        }
    }
    return(s / n)
}
