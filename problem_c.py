# Problem C

# Given the path intersections of a group of people as they cross the street
# find the size of the largest group whose paths all mutually intersect


import sys


def recursive_intersections(all_intersections, people_tracker, current_set, memo):
    """
        Recursively searches intersects the set of people a person has met in order
        to find the largest group of people whose paths have all mutually met
    """

    if current_set == memo:             # Set is current solution
        return memo
    if len(current_set) < len(memo):    # Sets smaller than the current solution are excluded
        return memo
    if current_set == people_tracker:   # Solution found
        memo = current_set
        return memo

    # Check intersections with people in the current_set but not the people_tracker
    for other_person in current_set - people_tracker:
        old_set = {*current_set}                        # Store the set
        current_set &= all_intersections[other_person]  # Set intersection
        people_tracker.add(other_person)

        # Check current_set or intersect with another person
        group = recursive_intersections(all_intersections, people_tracker, current_set, memo)

        current_set = {*old_set}                # Remove the intersection from above
        people_tracker.remove(other_person)
        memo = group        # Update solution

    return memo


if __name__ == '__main__':
    fptr = sys.stdout

    numbers = input().split()
    num_people = int(numbers[0])
    num_people_met = int(numbers[1])

    all_intersections = {}  # Dictionary of groups whose paths have intersected

    for _ in range(num_people_met):
        (person_1, person_2) = input().split()

        if not all_intersections.get(person_1):             # Create person_1 set if it doesn't exist
            all_intersections[person_1] = set(person_1)
        all_intersections[person_1].add(person_2)           # Add person_2 to the set

        if not all_intersections.get(person_2):             # Same for person_2
            all_intersections[person_2] = set(person_2)
        all_intersections[person_2].add(person_1)

    memo = set()

    for person in all_intersections:
        current_set = all_intersections[person]     # Set of all people 'person' has intersected with
        people_tracker = set(person)

        # Find the largest group of people who have mutually intersected within current_set
        all_sets = recursive_intersections(all_intersections, people_tracker, current_set, memo)

        memo = set(person for person in all_sets)

    largest_group = len(memo)

    fptr.write(str(largest_group) + '\n')
    fptr.close()