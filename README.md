# pigeonhole-principle 

It calculates all the possibilities in any group. It results that always there will be a pair of people with the same amount of friends.

The explanation would be:

  There are two lists: A and B, which represent the amount of people in the world, and the maximum amount of friends someone can have.
  If there are n people -> A = {1, 2, 3, ... , n}, and B = {0, 1, 2, ... , n - 1}.

  Person A will be friend of Person B when: both P. A and P. B are willing to do so.
  This is an AND relation:
  
  ``` cpp
	  p = P. A is friendly with P. B;
	  q = P. B is friendly with P. A.
      _________________________________
      |   p   |   q   |  Friendship   |
      |-------------------------------|
      |   1   |   1   |       1       |
      |   0   |   1   |       0       |
      |   1   |   0   |       0       |
      |   0   |   0   |       0       |
      ---------------------------------
  ```

  Therefore: if somebodi chose to have 0 friends, no one can be friends to n-1 people.

  So, imagining that indeed somebody always chose to not have friends, 
  A will have n instances and B will have n-1, which leads to the fact that two people from A will share a value from B.

  If not (if everybody chose to have one friend), they would all have the same amount of them...
