nonogramRow <- function(x){
    r = c()
    a <- 0
    for(i in x){
        if(!a && i){ r = c(r, 1)}
        else if(i) { 
            j <- length(r)
            r[j] <- r[j] + 1
        }
        a <- i
    }
    return(r)
}
