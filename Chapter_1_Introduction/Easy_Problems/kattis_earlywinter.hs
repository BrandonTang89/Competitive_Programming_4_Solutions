-- Kattis - earlywinter
-- Simplish problem
-- Time: O(n), Space: O(n)
solve :: Int -> Int -> [Int] -> String
solve _ _ [] = "It had never snowed this early!"
solve n m (x:xs)
  | x <= m = "It hadn't snowed this early in " ++ show n ++ " years!"
  | otherwise = solve (n + 1) m xs

main :: IO () -- define type IO()
main = do
  x <- getLine -- x is a string
  let [n, dm] = map read (words x) :: [Int]
  l <- getLine
  let xs = map read (words l) :: [Int] -- split by spaces
  putStrLn (solve 0 dm xs)
