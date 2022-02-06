-- Kattis - twostones
-- Just check if x is even or odd
solve :: Integer -> String
solve n = if odd n then "Alice" else "Bob"

main = do
    strX <- getLine
    let x = (read strX :: Integer)

    putStrLn $ solve x