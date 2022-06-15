-- Kattis - babybites
-- Simplish recursive problem
-- Time: O(n), Space: O(n)
solve :: Int -> [String] -> Bool
solve _ [] = True
solve n ("mumble":xs) = solve (n+1) xs
solve n (x:xs) = if (n+1 == (read x :: Int)) then solve (n+1) xs else False

main :: IO () -- define type IO()
main = do
  x <- getLine -- x is a string
  let n = read x :: Int -- convert x to double

  l <- getLine
  let xs = (words l) :: [String] -- split by spaces
  putStrLn $ if solve 0 xs then "makes sense" else "something is fishy"
  