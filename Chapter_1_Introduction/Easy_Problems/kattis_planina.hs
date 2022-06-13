-- Kattis - planina
-- We can either solve the the number of dots per side analytically, or just define a simple recurence
-- formula as we do here. Then print the number of dots per side squared.
-- Time: O(n), Space: O(1)
compute_side :: Integer -> Integer
compute_side x = if x == 0 then 2 else (compute_side (x-1))*2 - 1

main :: IO()
main = do
    x <- getLine
    let y = compute_side (read x)

    print (y*y)