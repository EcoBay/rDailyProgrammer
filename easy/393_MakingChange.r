change <- function(x, denom = c(500, 100, 25, 10, 5, 1)){
    if(denom[1] == 1){return(x)}
    else{
        return(floor(x / denom[1]) + change(x %% denom[1], denom[2:length(denom)]))
    }
}

