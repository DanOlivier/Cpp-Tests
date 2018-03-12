def solution(A):
    events = []
    print "========================="
    print A
    for i, a in enumerate(A):
        events += [(i-a, +1), (i+a, -1)]
    print events
    events.sort(key=lambda x: (x[0], -x[1]))
    print events
    intersections, active_circles = 0, 0
    for _, circle_count_delta in events:
        intersections += active_circles * (circle_count_delta > 0)
        active_circles += circle_count_delta
        if intersections > 10E6:
            return -1
    print intersections
    return intersections


if __name__ == '__main__':
    print 'Start tests..'
    assert solution([]) == 0
    assert solution([1,0,0,3]) == 4

    assert solution([0, 0]) == 0
    assert solution([0, 1]) == 1
    assert solution([1, 1]) == 1
    assert solution([1, 2]) == 1
    assert solution([1, 3]) == 1
    assert solution([2, 1]) == 1
    assert solution([2, 2]) == 1
    assert solution([1, 0, 1]) == 3
    assert solution([2, 0, 0, 2]) == 5
    assert solution([2, 0, 0, 0, 2]) == 5
    assert solution([2, 0, 0, 0, 0, 2]) == 4

    assert solution([1, 5, 2, 1, 4, 0]) == 11

    print 'Ok!'
