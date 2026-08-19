pub fn sum(a: i32, b: i32) -> i32 {
    a + b
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sum_positive_numbers() {
        assert_eq!(sum(2, 3), 5);
    }

    #[test]
    fn sum_negative_numbers() {
        assert_eq!(sum(-2, -3), -5);
    }

    #[test]
    fn sum_zero() {
        assert_eq!(sum(7, 0), 7);
    }

    #[test]
    fn sum_commutative() {
        assert_eq!(sum(12, 34), sum(34, 12));
    }
}
