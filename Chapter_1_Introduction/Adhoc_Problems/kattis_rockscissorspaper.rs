/**Kattis - rockscissorspaper
 * My first question in Rust. Kinda as expected, there is a lot of extra code around,
 * particularly for handling IO... This is the effect of having to deal with the safety
 * aspect of rust I suppose. Also alot of "as usize" basically everywhere.
 * 
 * Time: O(hwn), Space: O(hw)
 */
use std::{collections::HashMap, io::stdin};
fn main() {
    let won_by: HashMap<i32, i32> = [(0, 2), (1, 0), (2, 1)].iter().cloned().collect();
    let dr = [0, 1, 0, -1];
    let dc = [1, 0, -1, 0];

    let mut ln: String = String::new();
    stdin().read_line(&mut ln).unwrap();
    let tc: i32 = ln.trim().parse().unwrap();

    for _ in 0..tc {
        ln = String::new();
        stdin().read_line(&mut ln).unwrap();
        let (h, w, n) = {
            let mut iter = ln.trim().split_whitespace();
            let h: i32 = iter.next().unwrap().parse().unwrap();
            let w: i32 = iter.next().unwrap().parse().unwrap();
            let n: i32 = iter.next().unwrap().parse().unwrap();
            (h, w, n)
        };

        let mut grid: Vec<Vec<Vec<i32>>> = vec![vec![vec![0; w as usize]; h as usize]; 2];

        for i in 0..h {
            ln = String::new();
            stdin().read_line(&mut ln).unwrap();
            for (j, c) in ln.trim().chars().enumerate() {
                grid[0][i as usize][j] = match c {
                    'R' => 0,
                    'S' => 1,
                    'P' => 2,
                    _ => -1,
                }
            }
        }

        for turn in 0..n {
            for r in 0..h {
                for c in 0..w {
                    for i in 0..4 {
                        let nr = r + dr[i];
                        let nc = c + dc[i];
                        if nr < 0 || nr >= h || nc < 0 || nc >= w {
                            continue;
                        }
                        if grid[(turn % 2) as usize][nr as usize][nc as usize]
                            == won_by[&grid[(turn % 2) as usize][r as usize][c as usize]]
                        {
                            grid[((turn + 1) % 2) as usize][r as usize][c as usize] =
                                grid[(turn % 2) as usize][nr as usize][nc as usize];

                            break;
                        } else {
                            grid[((turn + 1) % 2) as usize][r as usize][c as usize] =
                                grid[(turn % 2) as usize][r as usize][c as usize];
                        }
                    }
                }
            }
        }

        for i in 0..h {
            for j in 0..w {
                print!(
                    "{}",
                    match grid[((n) % 2) as usize][i as usize][j as usize] {
                        0 => 'R',
                        1 => 'S',
                        2 => 'P',
                        _ => ' ',
                    }
                );
            }
            println!();
        }
        println!();
    }
}
