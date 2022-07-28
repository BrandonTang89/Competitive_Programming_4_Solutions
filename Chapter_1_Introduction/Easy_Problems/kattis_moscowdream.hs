-- Kattis - moscowdream
-- Simply use a few ifs put together

-- Time: O(1), Space: O(1)
main :: IO ()
main = do
    args <- getLine
    let line = map read (words args) :: [Int]
    let a = line !! 0
    let b = line !! 1
    let c = line !! 2
    let n = line !! 3

    let result = if (a <= 0 || b <= 0 || c <= 0 || (a+b+c) < n || n < 3) then "NO" else "YES"
    putStrLn result