#
#
#

def get_url(s):
    base_url = f'https://docs.google.com/spreadsheets/d/1pJ-jeDmVb69yCgUbi0DsRT-HW8jfJlZBh6ehyelOaOw/export?gid=%d&format=csv'

    if s == 'data/reloading_data - powder burning rate chart.csv':
        return base_url % 0
    if s == 'data/reloading_data - CATRIDGES.csv':
        return base_url % 1775574147
    if s == 'data/reloading_data - 9mm parabellum.csv':
        return base_url % 1119510158
    if s == 'data/reloading_data - 38 special.csv':
        return base_url % 1030409937
    if s =='data/reloading_data - 357 magnum.csv':
        return base_url % 847084052
    if s =='data/reloading_data - 38 special +P.csv':
        return base_url % 2054435826
    if s == 'data/reloading_data - 7.62x39 russian.csv':
        return base_url % 483618626
    if s == 'data/reloading_data - 7.62x54 russian.csv':
        return base_url % 1053150830
    
    raise Exception("Unknown filename: " + s)