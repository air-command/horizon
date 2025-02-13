// Commands that can be sent to the launcher
var fillCMD     = 0;        // when true, the launcher should open the fill valve, when 0 it should shut the fill valve
var ventCMD     = 0;        // when true the launcher should open the vent valve. 
var launchCMD   = 0;        // When true the launcher should activate the release head servo motor

var fillArm 	= false;	// if control of fill has been armed
var ventArm 	= false;	// if control of vent has been armed
var launchArm	= false;	// if launch has been armed

var disabledBackCol = "#444444";
var enabledCol      = "#88FF88";
var toggledOffCol   = "#FFFFFF";
var toggledOnCol    = "#88FF88";
var buttonDownCol   = "#FF8888";


function initIO() {
    $.ajax({
        type: "POST",
        url: 'init.php',
        data: {name: 'test'},
        success: function(data){
//           alert(data);
        },
        error:function(jqXHR, textStatus, errorThrown) {
//alert(errorThrown);
            if(textStatus==="timeout") { 
                console.log("timeout error");	// Handle timeout error
            } else { 
                console.log("init error");	// Handle general comms error
            }
        }

    });
}

function controlIO() {
    $.ajax({
        type: "POST",
        url: 'control.php',
        data: {fill:   fillCMD, 
               vent:   ventCMD, 
               launch: launchCMD},
        success: function(data){
//            alert(data);
        },
        error:function(jqXHR, textStatus, errorThrown) {
            if(textStatus==="timeout") { 
                console.log("timeout error");	// Handle timeout error
            } else { 
                console.log("control error");	// Handle general comms error
            }
        }
    });

}

function connectIO(connectCMD) {
    $.ajax({
        type: "POST",
		url: 'connect.php',
		async: false,
        data: {connect: connectCMD},
        success: function(data){
//            alert(data);
        },
        error:function(jqXHR, textStatus, errorThrown) {
            if(textStatus==="timeout") { 
                console.log("timeout error");	// Handle timeout error
            } else { 
                console.log("init error");	// Handle general comms error
            }
        }

    });
}

/*

function saveImage() {
	var dataURL = renderer.view.toDataURL('image/png');		//take a snapshot of the rendered stage.
	$.ajax({
		method: 'POST',
		url: '../photo_upload.php',
		data: {
			photo: dataURL,
			game: "launchSnapshot"
		}
	});
}
*/

var launch = function(state) {
    launchCMD = state;
    controlIO();
    updateUI();
}

var fill = function(state) {
    fillCMD = state;
    controlIO();
    updateUI();
}

var vent = function(state) {
    ventCMD = state;
    controlIO();
    updateUI();
}

// Arm control button handler
var armFill = function() {
    fillArm  = !fillArm ;	//toggle arm state
    updateUI();
}

// Vent control button handler
var armVent = function() {
    ventArm  = !ventArm ;	//toggle arm state
    updateUI();
}

// Arm Launch button handler
var armLaunch = function() {
	launchArm = !launchArm;		//toggle arm state
    updateUI();
}

var updateUI = function() {
	if(launchArm) {
		// enable launch button
        $("#launchBtn").prop('disabled', false);
        if(launchCMD) {
            $("#launchBtn").css('background-color', buttonDownCol);
        } else {
            $("#launchBtn").css('background-color', enabledCol);
        }
        $("#armLaunchBtn").css('background-color', toggledOnCol);
	} else {
		// disable launch button
		$("#launchBtn").prop('disabled', true);
        $("#launchBtn").css('background-color', disabledBackCol);
        $("#armLaunchBtn").css('background-color', toggledOffCol);
	}

	if(fillArm) {
		// enable fill button
		$("#fillBtn").prop('disabled', false);
        if(fillCMD) {
            $("#fillBtn").css('background-color', buttonDownCol);
        } else {
            $("#fillBtn").css('background-color', enabledCol);
        }
        $("#armFillBtn").css('background-color', toggledOnCol);
	} else {
		// disable fill button
		$("#fillBtn").prop('disabled', true);
        $("#fillBtn").css('background-color', disabledBackCol);
        $("#armFillBtn").css('background-color', toggledOffCol);
    }

	if(ventArm) {
		// enable vent button
        $("#ventBtn").prop('disabled', false);
        if(ventCMD) {
            $("#ventBtn").css('background-color', buttonDownCol);
        } else {
            $("#ventBtn").css('background-color', enabledCol);
        }
        $("#armVentBtn").css('background-color', toggledOnCol);
	} else {
		// disable vent button
		$("#ventBtn").prop('disabled', true);
        $("#ventBtn").css('background-color', disabledBackCol);
        $("#armVentBtn").css('background-color', toggledOffCol);
    }
    
}

var key1Down = false;
var key2Down = false;
var key3Down = false;
var key4Down = false;
var key5Down = false;
var key6Down = false;

var load = function () {
    initIO();   // tell the IO pins to initialize
    
	var userAgent = navigator.userAgent.toLowerCase();
	var ios = (/iphone|ipad|ipod/i.test(userAgent));
	var android = (/Android/i.test(userAgent));
    //Initialize the UI
	var mobile = ios || android;
	console.log("mobile: " + mobile);
	if(mobile) {
		$("#launchBtn").on("touchstart",function(e) {if(launchArm)launch(1); e.preventDefault();});
		$("#launchBtn").on("touchend",  function(e) {if(launchArm)launch(0); e.preventDefault();});
		$("#fillBtn").on("touchstart",  function(e) {if(fillArm) fill(1); e.preventDefault();});
		$("#fillBtn").on("touchend",    function(e) {if(fillArm) fill(0); e.preventDefault();});
		$("#ventBtn").on("touchstart",  function(e) {if(ventArm) vent(1); e.preventDefault();});
		$("#ventBtn").on("touchend",    function(e) {if(ventArm) vent(0); e.preventDefault();});
	} else {
		$("#launchBtn").on("mousedown",function(e) {if(launchArm) launch(1); e.preventDefault();});
		$("#launchBtn").on("mouseup",  function(e) {if(launchArm) launch(0); e.preventDefault();});
		$("#launchBtn").on("mouseout", function(e) {if(launchArm) launch(0); e.preventDefault();});
		$("#fillBtn").on("mousedown",  function(e) {if(fillArm) fill(1); });
		$("#fillBtn").on("mouseup",    function(e) {if(fillArm) fill(0); });
		$("#fillBtn").on("mouseout",   function(e) {if(fillArm) fill(0); });
		$("#ventBtn").on("mousedown",  function(e) {if(ventArm) vent(1); });
		$("#ventBtn").on("mouseup",    function(e) {if(ventArm) vent(0); });
		$("#ventBtn").on("mouseout",   function(e) {if(ventArm) vent(0); });
	}
    $("#armFillBtn").on("click",   function() {armFill(); });
    $("#armVentBtn").on("click",   function() {armVent(); });
    $("#armLaunchBtn").on("click", function() {armLaunch(); });
	
	document.addEventListener('keydown', function(event) {
        var update = false;
        switch(event.keyCode) {
            case 49:    //'1'
                if(!key1Down) {
                    armVent();
                    key1Down = true;
                    update = true;
            }
            break;            

            case 54:    //'6'
            if(!key2Down) {
                armFill();
                key2Down = true;
                update = true;
            }
            break;            

            case 48:    //'0'
            if(!key3Down) {
                armLaunch();
                key3Down = true;
                update = true;
            }
            break;            

            case 65:    //'A'
            if(!key4Down) {
                if(ventArm) { 
                    vent(1) 
                };
                key4Down = true;
                update = true;
            }
            break;            

            case 32:    //' '
            if(!key5Down) {
                if(fillArm) { 
                    fill(1);
                }
                key5Down = true;
                update = true;
            }
            break;            

            case 76:    //'L'
            if(!key6Down) {
                if(launchArm) { 
                    launch(1); 
                }
                key6Down = true;
                update = true;
            }
            break;            
        }
        if(update) {
            event.preventDefault();
            updateUI();
        }
	});		

	document.addEventListener('keyup', function(event) {
        var update = false;

        switch(event.keyCode) {
            case 49:
                if(key1Down) {
                    key1Down = false;
                    update = true;
                }
            break;

            case 54:
                if(key2Down) {
                    key2Down = false;
                    update = true;
                }
            break;

            case 48:
                if(key3Down) {
                    key3Down = false;
                    update = true;
                }
            break;

            case 65:    //'A'
                if(key4Down) {
                    if(ventArm) { 
                        vent(0) 
                    };
                    key4Down = false;
                    update = true;
                }
            break;            

            case 32:    //' '
                if(key5Down) {
                    if(fillArm) { 
                        fill(0);
                    }
                    key5Down = false;
                    update = true;
                }
            break;            

            case 76:    //'L'
            if(key6Down) {
                if(launchArm) { 
                    launch(0); 
                }
                key6Down = false;
                update = true;
            }
            break;            
        }

        if(update) {
            event.preventDefault();
            updateUI();
        }
    
	});		
    
    updateUI();
};

var unloadPage = function() {
	connectIO(0);
}
