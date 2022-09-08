use std::io;

fn main() -> io::Result<()>{

    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    let n: i32 = input.trim().parse().unwrap();

    for _i in 0..n {
        let mut input1 = String::new();
        io::stdin().read_line(&mut input1)?;
        let size: usize = input1.trim().parse().unwrap();
        let mut input2 = String::new();
        let mut input3 = String::new();
        io::stdin().read_line(&mut input2)?;
        io::stdin().read_line(&mut input3)?;

        println!("{}", solve(size, input2, input3));
    }

    Ok(())
}


fn solve(size : usize, str1 : String, str2 : String) -> &'static str {


    for i in 0..size {
        if (str1.chars().nth(i).unwrap() == 'R') ^ (str2.chars().nth(i).unwrap() == 'R') {
            return "NO"
        }
    }

    "YES"
}