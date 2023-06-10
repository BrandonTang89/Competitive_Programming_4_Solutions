-- Kattis - lawnmower
-- Generally easy. Parsing the input is lowkey the hardest part.
import Data.List
main :: IO()
main = interact (unlines . map printSol . solve . map words . lines)

printSol :: Bool -> String
printSol True = "YES"
printSol False = "NO"

solve :: [[String]] -> [Bool]
solve ([_, _, d']:xs':ys':zs) = let d = read d' :: Double -- d is the diameter of the cutter
                                    xs = map read xs' :: [Double]
                                    ys = map read ys' :: [Double]
                                in (solver (75.0) (d/2.0) (sort xs) && solver (100.0) (d/2.0) (sort ys)) : solve zs
solve ([_, _, _]:[]) = []
solve _ = error "Unhandled case"

solver :: Double -> Double -> [Double] -> Bool -- total length, radius of cutter, list of centers
solver tl r xs = all (uncurry (>=)) (zip (map (+ r) xs) (tail (map (+ (-r)) xs))) && (head xs - r <= 0) && (last xs + r >= tl)