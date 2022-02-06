-- Kattis - ratingproblems
-- Simple question, assume all remaining judges vote either +3 or -3
maxRating, minRating :: (Int, Int, [Int]) ->  Double
maxRating (n, k, xs) = fromIntegral(3*(n-k) + sum xs) / fromIntegral(n)
minRating (n, k, xs) = fromIntegral((-3)*(n-k) + sum xs) / fromIntegral(n)

getKLines :: Int -> IO [Int]
getKLines 0 = return []
getKLines k = do
    line <- getLine
    rest <- getKLines (k-1)
    return ((read line :: Int):rest)

main = do
    args <- getLine
    let argsList = words args
    let n = read (argsList!!0) :: Int
    let k = read (argsList!!1) :: Int
    xs <- getKLines k 

    putStrLn (show (minRating (n, k, xs)) ++ " " ++  show (maxRating (n, k, xs)))