-- Kattis - deathtaxes
-- Just define a foldl
main :: IO()
main = interact (show . snd . foldl op (0, 0.0) . map (words) . lines)

op :: (Int, Double) -> [String] -> (Int, Double)
op (n, ave) ["buy", x, y] = (n + (read x), (ave * (fromIntegral n) + (read x) * (read y)) / (fromIntegral (n + (read x))))
op (n, ave) ["sell", x, _] = (n - (read x), ave)
op (n, ave) ["split", x] = (n * (read x), ave/(read x))
op (n, ave) ["merge", x] = (n `div` (read x), ave*(read x))
op (n, ave) ["die", y] = let taxPer = max (((read y) - ave)*0.3) 0.0
                            in (0, fromIntegral n * ((read y) - taxPer))
op _ _ = error "error"