use std::io;
use std::collections::HashMap;

fn main() -> io::Result<()>{

    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    let n: i32 = input.trim().parse().unwrap();

    for _i in 0..n {

        let mut input1 = String::new();
        io::stdin().read_line(&mut input1)?;
        let size: usize = input1.trim().parse().unwrap();

        let mut input2 = String::new();
        io::stdin().read_line(&mut input2)?;
        let vec1: Vec<&str> = input2.trim().split_whitespace().collect();


        let mut input3 = String::new();
        io::stdin().read_line(&mut input3)?;
        let vec2: Vec<&str> = input3.trim().split_whitespace().collect();


        let mut input4 = String::new();
        io::stdin().read_line(&mut input4)?;
        let vec3: Vec<&str> = input4.trim().split_whitespace().collect();

        my_print(solve(size, vec1, vec2, vec3));
    }

    Ok(())
}


fn solve(_size : usize, str1 : Vec<&str>, str2 : Vec<&str>, str3 : Vec<&str>) -> Vec<i32> {
    let mut map = HashMap::new();

    for vec in [&str1, &str2, &str3]{
        for s3 in vec{
            *map.entry(s3).or_insert(0) += 1;
        }
    }

    let mut answ = Vec::new();

    for vec in [&str1, &str2, &str3]{
        let mut sum = 0;
        for s3 in vec{
            match map.get(s3) {
                Some(1) => sum += 3,
                Some(2) => sum += 1,
                _ => (),
            }
        }
        answ.push(sum);
    }

    answ
}

fn my_print(vec: Vec<i32>) -> () {
    for val in vec {
        print!("{} ", val);
    }
    println!{};
}