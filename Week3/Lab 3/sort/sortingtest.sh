test_quantity()
{
  echo $TYPE $TEST_QUANTITY\k

  { time ./sort$SORT_N $TYPE$TEST_QUANTITY\000.txt > /dev/null; } 2>&1 | grep real | tr -d 'real ' | xargs
  echo

}

test_type()
{
  TEST_QUANTITY=5
  test_quantity
  TEST_QUANTITY=10
  test_quantity
  TEST_QUANTITY=50
  test_quantity
}

test_sort() 
{
  echo sort$SORT_N

  TYPE=random
  test_type
  TYPE=reversed
  test_type
  TYPE=sorted
  test_type
  echo
  
}

SORT_N=1
test_sort
SORT_N=2
test_sort
SORT_N=3
test_sort
