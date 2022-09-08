use std::io;

fn main() -> io::Result<()>{

    let n: usize = {
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        input.trim().parse().unwrap()
    };

    for _i in 0..n {

        let size: usize = {
            let mut input1 = String::new();
            io::stdin().read_line(&mut input1)?;
            input1.trim().parse().unwrap()
        };

        let str: Vec<char> = {
            let mut input2 = String::new();
            io::stdin().read_line(&mut input2)?;
            input2.trim().chars().collect()
        };

        solve(size, str);
    }

    Ok(())
}


fn solve(size : usize, str : Vec<char>) -> () {
    let mut changes = Vec::new();
    let mut sum = 0;

    for i in 0..size{
        let c = str[i];
        let curr: i64;
        let ncurr: i64;
        match c {
            'L' => {curr = i as i64; ncurr = size as i64 - i as i64 - 1},
            _ => {ncurr = i as i64; curr = size as i64 - i as i64 - 1},
        };

        sum += curr;
        changes.push(ncurr - curr);
         
    }
    changes.sort_by(|a, b| b.cmp(a));

    for i in 0..changes.len(){
        let change = changes.get(i).unwrap();
        if change > &0 {
            sum += change;
        }
        print!("{} ", sum);
    }

    println!{};

}