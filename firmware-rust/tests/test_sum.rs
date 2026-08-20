use firmware_rust::math::sum;

#[test]
fn integration_sum_positive_numbers() {
    assert_eq!(sum(2, 3), 5);
}

#[test]
fn integration_sum_negative_numbers() {
    assert_eq!(sum(-2, -3), -5);
}

#[test]
fn integration_sum_zero() {
    assert_eq!(sum(7, 0), 7);
}

#[test]
fn integration_sum_commutative() {
    assert_eq!(sum(12, 34), sum(34, 12));
}
