-- Kattis - grandadventure
-- Just do a big finite state automata, it may be ugly but it works.
main :: IO()
main = interact(unlines . map (getText . solve []) . tail . lines)

getText :: Bool -> String
getText True = "YES"
getText False = "NO"

solve :: String -> String -> Bool
solve [] [] = True
solve _ [] = False -- stuff left
solve bag ('.':xs) = solve bag xs
solve ('|':bag) ('t':xs) = solve bag xs
solve (_:bag) ('t':xs) = solve bag ('t':xs)
solve [] ('t':xs) = False
solve ('$':bag) ('b':xs) = solve bag xs
solve (_:bag) ('b':xs) = solve bag ('b':xs)
solve [] ('b':xs) = False
solve ('*':bag) ('j':xs) = solve bag xs
solve (_:bag) ('j':xs) = solve bag ('j':xs)
solve [] ('j':xs) = False
solve bag (c:xs)
    | c == '$' || c == '|' || c == '*' = solve (c:bag) xs
    | otherwise = error ("Invalid input: " ++ show (c:xs))