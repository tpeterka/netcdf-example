# producer callbacks
def prod_callback(vol, rank):

    print("prod_callback")

    # define a callback to enter barrier after a file close in passthru mode
    def afc_cb(name):
        print("prod_callback afc_cb: name =", name)
        if vol.is_passthru(name, "*") == True:
            vol.serve_all(True, False)

    # define a callback on dataset write as a test
    def adw_cb():
        print("prod_callback adw_cb")

    # set the callback
#     vol.set_after_file_close(afc_cb)
    vol.set_after_dataset_write(adw_cb)
    vol.set_send_filename(afc_cb)

    vol.set_keep(True);
    vol.serve_on_close = False

# consumer callbacks
def con_callback(vol, rank):

    print("con_callback")

    # define a callback to enter barrier before a file open in passthru mode
    def bfo_cb(name):
        print("con_callback bfo_cb: name =", name)
        if vol.is_passthru(name, "*") == True:
            vol.get_filenames(0)

    # define a callback after file close as a test
    def afc_cb(name):
        print("con_callback afc_cb: name =", name)

    # set the callback
#     vol.set_before_file_open(bfo_cb)
    vol.set_after_file_close(afc_cb)

#     vol.set_keep(True);
