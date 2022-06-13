-- Kattis - romans
-- Just follow the description
-- Time: O(1), Space: O(1)
toRom :: Double -> Integer -- Whatever function we need to use
toRom x = round (x * 1000 * 5280.0 / 4854.0)

main :: IO () -- define type IO()
main = do
  x <- getLine -- x is some string
  let y = read x :: Double -- convert x to
  print (toRom y)
