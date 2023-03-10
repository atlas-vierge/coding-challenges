# sqlite database for storing account info

import sqlite3

def open_data_base():
    connection = sqlite3.connect("cc_accounts.db")
    the_cursor = connection.cursor()
    return connection, the_cursor

def close_data_base(connection):
    connection.commit()
    connection.close()


# Create--if one doesn't already exist--a sqlite
# data_base for the tiger_log.
def create_table():
    conn, cursor = open_data_base()
    cursor.execute("CREATE TABLE IF NOT EXISTS CC_Accounts (name, cc_number, balance)")
    close_data_base(conn)



# Do a batch insert.  
# Parameters: a list where every row 
# has a date, camera_id, and absolute path.
# data_and_camera = [(2013/10/12/12, cam, abs_path), (2013/10/12/13, cam, abs_path)]
# for example.
def insert_many_rows(date_camera_absolute):
    conn, cursor = open_data_base() 
    cursor.executemany("INSERT OR IGNORE INTO tiger_log(date, camera_id, abs_path) values(?,?,?)",date_camera_absolute)
    close_data_base(conn)


# Insert one row to the data_base with
# a date, camera id, and abs_path
def insert_row(date, camera_id, abs_path):
    conn, cursor = open_data_base() 
    abs_path = remove_duplicate_slashes(abs_path)
    cursor.execute("INSERT OR IGNORE INTO tiger_log(date, camera_id, abs_path) values(?,?,?)", (date, camera_id, abs_path))
    close_data_base(conn)



# Update the Y/N processed field for a 
# particular camera at a given date (update 1 row)
# Parameters: date of the row to be updated
# camera_id of the row to be updated
# processed: Y = is processed, N = is NOT processed
# Return: True on success, False on failure
def update_processed(date, camera_id, processed):
    if processed == "Y" or processed == "N":
        conn, cursor = open_data_base() 
        cursor.execute("UPDATE tiger_log SET processed = ? WHERE date = ? AND camera_id = ?",(processed, date, camera_id))  
        close_data_base(conn)
        return True
    else:
        print "The processed field must be Y/N."
        return False



# Update the Y/N processed field for a 
# particular camera at a given date (update 1 row)
# Parameters: date of the row to be updated
# camera_id of the row to be updated
# processed: Y = is processed, N = is NOT processed
# Return: True on success, False on failure
def update_processed_by_dir(abs_dir, processed):
    if processed == "Y" or processed == "N":
        conn, cursor = open_data_base() 
        abs_dir = remove_duplicate_slashes(abs_dir)
        cursor.execute("UPDATE tiger_log SET processed = ? WHERE abs_path = ?",(processed, abs_dir))  
        close_data_base(conn)
        return True
    else:
        print "The processed field must be Y/N."
        return False



# Update the number of positive frames for a 
# particular camera at a given date (update 1 row)
# Parameters: date of the row to be updated
# camera_id of the row to be updated
# num_pos: # of positive frames found for this entry
def update_pos_frames(date, camera_id, num_pos):
    conn, cursor = open_data_base() 
    cursor.execute("UPDATE tiger_log SET pos_frames = ? WHERE date = ? AND camera_id = ?",(num_pos, date, camera_id))  
    close_data_base(conn)


# Update the number of positive frames for a 
# particular camera at a given abs directory
# Parameters: abs directory of the video files
# num_pos: # of positive frames found for this entry
def update_pos_frames_by_dir(abs_dir, num_pos):
    conn, cursor = open_data_base() 
    abs_dir = remove_duplicate_slashes(abs_dir)
    cursor.execute("UPDATE tiger_log SET pos_frames = ? WHERE abs_path = ?",(num_pos, abs_dir))  
    close_data_base(conn)


# Update the directory where positive footage
# for a particular camera at a given abs directory
# Parameters: abs directory of the video files
# positive_dir: dir where positive footage is saved
def update_savedat_by_dir(abs_dir, positive_dir):
    conn, cursor = open_data_base() 
    abs_dir = remove_duplicate_slashes(abs_dir)
    positive_dir = remove_duplicate_slashes(positive_dir)
    cursor.execute("UPDATE tiger_log SET saved_at = ? WHERE abs_path = ?",(positive_dir, abs_dir))    
    close_data_base(conn)


# Update the Y/N concatenated field for a 
# particular camera at a given date (update 1 row)
# Parameters: abs_dir
# processed: Y = is processed, N = is NOT processed
# Return: True on success, False on failure
def update_concatenated_by_dir(abs_dir, processed):
    if processed == "Y" or processed == "N":
        conn, cursor = open_data_base() 
        abs_dir = remove_duplicate_slashes(abs_dir)
        cursor.execute("UPDATE tiger_log SET concatenated = ? WHERE abs_path = ?",(processed, abs_dir))  
        close_data_base(conn)
        return True
    else:
        print "The processed field must be Y/N."
        return False


# Update the Y/N concatenated field for a 
# particular camera at a given date (update 1 row)
# Parameters: the saved_at dir
# processed: Y = is processed, N = is NOT processed
# Return: True on success, False on failure
def update_concatenated_by_saved_dir(saved_dir, processed):
    if processed == "Y" or processed == "N":
        conn, cursor = open_data_base() 
        saved_dir = remove_duplicate_slashes(saved_dir)
        cursor.execute("UPDATE tiger_log SET concatenated = ? WHERE saved_at = ?",(processed, saved_dir))  
        close_data_base(conn)
        return True
    else:
        print "The processed field must be Y/N."
        return False





# Select the rows that are unprocessed (the processed column
# is not marked, or marked no.)
# Return: a tuple of tuples. Each of the inner tuples 
# represent a row in the table (contains the abs_paths)
def select_unprocessed():
    conn, cursor = open_data_base() 
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT abs_path FROM tiger_log WHERE processed IS null OR processed = '' or processed = 'N'")
    unprocessed = cursor.fetchall()
    close_data_base(conn)
    return unprocessed


# Select the rows that are processed (the processed column
# is marked 'Y'.) and not concatenated.
# Return: a tuple of tuples. Each of the inner tuples 
# represent a row in the table (contains the saved_at paths)
def select_processed_not_concatenated():
    conn, cursor = open_data_base() 
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT saved_at FROM tiger_log WHERE processed = 'Y' AND concatenated IS NULL OR concatenated = ''")
    processed = cursor.fetchall()
    close_data_base(conn)
    return processed



# Select the rows with corresponding passed in dates
# Return: the path to their positive footage
# positive footage (possibly none)
def select_date(date):
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT saved_at FROM tiger_log WHERE date = ?", [date])
    dated = cursor.fetchall()
    close_data_base(conn)
    return dated


# Select the rows that have saved positive footage.
# Return: all the dates that have positive footage saved.
def select_dates_with_pos_footage():
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT date FROM tiger_log WHERE saved_at IS NOT null OR saved_at != ''")
    dates = cursor.fetchall()
    close_data_base(conn)
    return dates


# Select the rows that have saved positive footage.
# Return: all the directories that have positive footage saved.
def select_dirs_with_pos_footage():
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT saved_at FROM tiger_log WHERE saved_at IS NOT null OR saved_at != ''")
    directories = cursor.fetchall()
    close_data_base(conn)
    return directories



# Select the rows that have saved  footage
# and the given date.
# Return: all the directories that have concatenated footage saved.
def select_dirs_with_positive_footage(date):
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT saved_at FROM tiger_log WHERE saved_at IS NOT null and date = ?", [date])
    directories = cursor.fetchall()
    close_data_base(conn)
    return directories




# Select the rows that have saved concatenated footage
# and the given date.
# Return: all the directories that have concatenated footage saved.
def select_dirs_with_concatenated_footage(date):
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT saved_at FROM tiger_log WHERE concatenated = 'Y' and date = ?", [date])
    directories = cursor.fetchall()
    close_data_base(conn)
    return directories



# Select the rows that have saved concatenated footage.
# Return: all the dates that have concatenated footage saved.
def select_dates_with_concatenated_footage():
    conn, cursor = open_data_base()
    conn.row_factory = sqlite3.Row
    cursor.execute("SELECT date FROM tiger_log WHERE concatenated = 'Y'")
    dates = cursor.fetchall()
    close_data_base(conn)
    return dates









