def check_nested(input):
  opened_cnt = 0
  closed_cnt = 0
  pair_cnt = 0
  count_pars = 0

  for c in input:
    if c == '(':
      opened_cnt += 1
      count_pars += 1
    if c == ')':
      count_pars += 1
      if opened_cnt > 0:
        closed_cnt += 1

    if opened_cnt > 0 and closed_cnt > 0:
      opened_cnt -= 1
      closed_cnt -= 1

      pair_cnt += 1

  if pair_cnt == count_pars/2:
    return True
  else:
    return False


a = "()()()()()()"
if check_nested(a) == True:
  print(f"\"{a}\" has properly nested parentheses.")
else:
  print(f"\"{a}\" doesn't have properly nested parentheses.")
