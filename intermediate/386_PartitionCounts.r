count_partition <- function(x){
    if (x %in% 0:1) return(1)
    else {
        memo <- array(1, dim = x + 1)

        for(j in 2:x){
            res <- 0
            a <- 1
            i <- 0

            while(a <= j){
                op <- if(bitwShiftR(i, 1) %% 2) -1 else 1
                res <- res + op * memo[j - a + 1]

                a <- a + if (i %% 2) i + 2 else i / 2 + 1
                i <- i + 1
            }

            memo[j + 1] <- res
        }

        return (memo[x + 1])
    }
}

count_partition(666666)
