-- Kattis - symmetricorder
-- Simple stuff
main :: IO()
main = interact(unlines . parse [1..] . lines)

parse :: [Int] -> [String] -> [String]
parse (i:is) (n':xs) = if n /= 0 then (("SET " ++ show i):(solve ys [] [])) ++ parse is zs else []
                        where n = read n' :: Int
                              (ys, zs) = splitAt n xs
parse _ _ = error "Invalid input"

solve :: [String] -> [String] -> [String] -> [String]
solve [] ys zs = reverse ys ++ zs
solve (x:y:xs) ys zs = solve xs (x:ys) (y:zs)
solve [x] ys zs = solve [] (x:ys) zs