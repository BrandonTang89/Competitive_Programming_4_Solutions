-- Kattis - cold
-- Simple counting problem, just do a linear pass on the array
-- Time: O(n), Space: O(n)
solve :: Int -> [Int] -> Int
solve n [] = n
solve n (x:xs) =
  if (x < 0)
    then solve (n + 1) xs
    else solve n xs

main :: IO () -- define type IO()
main = do
  x <- getLine -- x is a string
  let n = read x :: Int -- convert x to double
  l <- getLine
  let xs = map read (words l) :: [Int] -- split by spaces
  print (solve 0 xs)
